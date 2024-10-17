import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session,  url_for
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

# From week 9:
from helpers import apology, login_required

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure SQLite database
db = SQL("sqlite:///dreams.db")  # db is the variable which stores our data


@app.route("/")
@login_required
def index():
    """Main Page"""
    user_id = session["user_id"]
    dreams_db = db.execute("SELECT strftime('%d/%m/%Y', dream_date) AS formatted_date, description, lucid, cat_name FROM dreams INNER JOIN dreams_categories ON dreams.dream_id = dreams_categories.dream_id INNER JOIN categories ON categories.cat_id = dreams_categories.cat_id WHERE dreams.user_id = ? ORDER BY dream_date DESC", user_id)
    return render_template("mydreams.html", dreams=dreams_db)

@app.route("/categories", methods=["GET", "POST"])
@login_required
def categories():
    """See and Add Categories"""
    if request.method == "GET":
        user_id = session["user_id"]
        categories = db.execute("SELECT cat_id, cat_name FROM categories WHERE user_id = ?", user_id)
        return render_template("categories.html", categories=[row["cat_name"] for row in categories])
    else:
        cat_name_input = request.form.get("category")

        # Check if category already exists (case-insensitive)
        user_id = session["user_id"]
        cat_name = cat_name_input.lower()
        existing_cats = db.execute("SELECT cat_name FROM categories WHERE user_id = ?", user_id)
        existing_cat = any(cat_name == row["cat_name"].lower() for row in existing_cats)

        if existing_cat:
            flash("Category name already exists", "error")
        else:
            # register category into database
            if cat_name:
                user_id = session["user_id"]
                db.execute("INSERT INTO categories (user_id, cat_name) VALUES (?, ?)", user_id, cat_name)
                flash("Category added!", "success")
            else:
                flash("Category name cannot be empty", "error")

        # Shows updated categories
        categories = db.execute("SELECT cat_name FROM categories WHERE user_id = ?", user_id)
        categories = [row["cat_name"].title() for row in categories]
        return render_template("categories.html", categories=categories)


@app.route("/newdream", methods=["GET", "POST"])
@login_required
def newdream():
    """Register a New Dream"""
    if request.method == "GET":
        user_id = session["user_id"]
        categories = db.execute("SELECT cat_name FROM categories WHERE user_id = ? ORDER BY cat_name ASC", user_id)
        return render_template("newdream.html", categories=[row["cat_name"] for row in categories])
    else:
        lucid = request.form.get("lucid")
        description = request.form.get("description")
        cat_name = request.form.get("category")

        if not request.form.get("description"):
            flash("Your forgot to write something...")
            return redirect(url_for('newdream'))

        elif not request.form.get("category"):
            flash("Choose at least one category!")
            return redirect(url_for('newdream'))

        else:

            # Register date and time of registration
            dream_date = datetime.now()

            # register dream into database
            user_id = session["user_id"]
            db.execute("INSERT INTO dreams (user_id, lucid, description, dream_date) VALUES (?, ?, ?, ?)", user_id, lucid, description, dream_date)

            # Get dream_id
            dream_id = db.execute("SELECT last_insert_rowid()")[0]["last_insert_rowid()"]

            # Get cat_id
            cat_id_query = db.execute("SELECT cat_id FROM categories WHERE user_id = ? AND cat_name = ?", user_id, cat_name)

            # Verifique se há resultados na consulta
            if cat_id_query:
                # Se houver resultados, pegue o primeiro resultado
                cat_id_result = cat_id_query[0]
                # Acesse o cat_id dentro do resultado
                cat_id = cat_id_result['cat_id']
                # Insira o sonho com a categoria correspondente
                db.execute("INSERT INTO dreams_categories (dream_id, cat_id) VALUES (?, ?)", dream_id, cat_id)
                flash("Dream added!", "success")
            else:
                flash("No matching category found", "error")


            return redirect(url_for('mydreams'))


@app.route("/mydreams")
@login_required
def mydreams():
    """Show history of dreams"""
    user_id = session["user_id"]
    dreams_db = db.execute("SELECT strftime('%d/%m/%Y', dream_date) AS formatted_date, description, lucid, cat_name FROM dreams INNER JOIN dreams_categories ON dreams.dream_id = dreams_categories.dream_id INNER JOIN categories ON categories.cat_id = dreams_categories.cat_id WHERE dreams.user_id = ? ORDER BY dream_date DESC", user_id)
    return render_template("mydreams.html", dreams=dreams_db)

# User registration
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    else:  # if the form is filled, run this code:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # if any field is empty, return apology:
        if not username:
            return apology("Username required")
        if not password:
            return apology("Password required")
        if not confirmation:
            return apology("Confirmation required")

        # check if password matches confirmation
        if password != confirmation:
            return apology("Passwords don't match")

        # Check if username already exists
        existing_user = db.execute("SELECT user_id FROM users WHERE username = ?", username)
        if existing_user:
            return apology("Username already exists")

        # encrypt password
        hash = generate_password_hash(password)

        # register user into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # Get the ID of the newly inserted user
        new_user_row = db.execute("SELECT user_id FROM users WHERE username = ?", username)
        new_user_id = new_user_row[0]["user_id"]

        # Store user using session - enter account without need for login after registering
        session["user_id"] = new_user_id

        return redirect("/")

# Login - from Week 9
@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["user_id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

# Logout - from Week 9
@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")
