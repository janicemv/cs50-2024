-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene description
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- Check interviews with the witnesses
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28;

-- In the bakery: Ruth, Eugene, Raymond. Check ATM, cars in the parking lot, purchased flight tickets for the next day. Eugene recognized the thief from the ATM.

-- Check ATM transactions
SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street';

-- Check bakery security logs
SELECT license_plate
FROM bakery_security_logs
WHERE month = 7 AND day = 28
AND hour = 10 AND minute BETWEEN 00 and 20;

SELECT caller, receiver
FROM phone_calls
WHERE month = 7 AND day = 28;

-- Thief activities: Cash withdrawal at the ATM -> Went to the bakery -> Robbed the duck -> Called someone -> Left the bakery by car -> Took a flight the next morning

-- The name of the people who were at the ATM and had a license plate recorded on the bakery at the date of the crime
SELECT name
FROM people
WHERE id IN
(
    SELECT person_id FROM bank_accounts
    WHERE account_number IN
    (
        SELECT account_number
        FROM atm_transactions
        WHERE month = 7 AND day = 28
        AND atm_location = 'Leggett Street'
    )

    INTERSECT

    SELECT id
    FROM people
    WHERE license_plate IN
    (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28
    AND hour = 10 AND minute BETWEEN 00 and 30
    )
);

-- Iman, Luca, Diana, Bruce were at the ATM and at the bakery on the moment of the crime

-- The name of the person with the license plate in the bakery whose passport was used the next day
SELECT name
FROM people
WHERE passport_number IN
(
    SELECT passport_number
    FROM passengers
    JOIN flights on passengers.flight_id = flights.id
    JOIN airports on airports.id = flights.origin_airport_id
    WHERE flights.origin_airport_id =
    (
        SELECT id from airports
        WHERE city = 'Fiftyville'
    )
    AND month = 7 AND day = 29
)

INTERSECT

SELECT name
FROM people
WHERE license_plate IN
    (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28
    AND hour = 10 AND minute BETWEEN 00 and 30
    );

-- Luca, Diana and Bruce appear again!

-- Check who called who at the moment of the crime with the other data that I had

SELECT p1.name as caller_name, p2.name as receiver_name, duration
FROM phone_calls
JOIN people p1 ON p1.phone_number = phone_calls.caller
JOIN people p2 ON p2.phone_number = phone_calls.receiver
WHERE month = 7 AND day = 28 AND duration < 60;

-- Bruce called Robin, Deborah, Gregory and Carl. The call with Robin lasted less than one minute.

-- Where did he go?

-- Where do the flights from Fiftyville go?
SELECT city1.city as origin, city2.city as destination, flights.id, day, hour, minute
FROM flights
JOIN airports city1 ON city1.id = flights.origin_airport_id
JOIN airports city2 ON city2.id = flights.destination_airport_id
WHERE month = 7 AND day = 29;

-- Boston, San Francisco, NY, Chicago, Tokyo - earlier flight is to NY (id=36)

SELECT name FROM people
WHERE passport_number IN
(
    SELECT passport_number
    FROM passengers
    JOIN flights on passengers.flight_id = flights.id
    JOIN airports on airports.id = flights.origin_airport_id
    WHERE flights.id = 36
AND month = 7 AND day = 29
);

-- Bruce and Luca again. But Luca did not call anyone! Checked the calls again and... voilà!
