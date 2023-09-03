-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Getting crime scene report
SELECT * FROM crime_scene_reports
    WHERE year = 2021 AND month = 7 AND day = 28 AND street LIKE 'humphrey street';


-- Getting information about the interviews took place on the same day and containing the word 'bakery'
SELECT * FROM interviews
    WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';


-- So the robbery took place at 10:15am and one witness said 10 minutes after the robbery he saw the thief running from parking lot
-- Now getting parking lot details from bakery security logs between 10 minutes after robbery
SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit';


-- Now getting data from atm transactions as witness mentioned about it, that robber did transaction at legget street on the same day
SELECT account_number FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE 'Leggett Street' AND transaction_type LIKE 'withdraw';


-- Now collecting data of the phone numbers of caller who spoke for less than 60 seconds as mentioned by the 3rd witness
SELECT caller FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;


-- Collecting passport numbers of the passengers who fled on 29th july 2021 on earliest flight from fiftyville as mentioned by the 3rd witness
SELECT passport_number FROM passengers
    JOIN flights ON flights.id = passengers.flight_id
    JOIN airports ON airports.id = flights.origin_airport_id
        WHERE year = 2021 AND month = 7 AND day = 29 AND city LIKE 'fiftyville' AND hour = 8;


-- Now comparing all the data we gathered before to get the person matching with all this information who is infact the thief
SELECT name FROM people
    JOIN bank_accounts ON bank_accounts.person_id = people.id
        WHERE account_number IN (SELECT account_number FROM atm_transactions
            WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE 'Leggett Street' AND transaction_type LIKE 'withdraw')
        AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
        AND passport_number IN (SELECT passport_number FROM passengers
            JOIN flights ON flights.id = passengers.flight_id
            JOIN airports ON airports.id = flights.origin_airport_id
                WHERE year = 2021 AND month = 7 AND day = 29 AND city LIKE 'fiftyville' AND hour = 8)
        AND license_plate IN (SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit');


-- Now Getting the name of thief's Accomplice by getting the receivers phone number as thief called to Accomplice
SELECT DISTINCT name FROM people
    WHERE phone_number IN (SELECT receiver FROM phone_calls
        WHERE caller IN (SELECT phone_number FROM people
            WHERE name IN (SELECT name FROM people
                JOIN bank_accounts ON bank_accounts.person_id = people.id
                    WHERE account_number IN (SELECT account_number FROM atm_transactions
                        WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE 'Leggett Street' AND transaction_type LIKE 'withdraw')
                    AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
                    AND passport_number IN (SELECT passport_number FROM passengers
                        JOIN flights ON flights.id = passengers.flight_id
                        JOIN airports ON airports.id = flights.origin_airport_id
                            WHERE year = 2021 AND month = 7 AND day = 29 AND city LIKE 'fiftyville' AND hour = 8)
                    AND license_plate IN (SELECT license_plate FROM bakery_security_logs
                        WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit')))
        AND year = 2021 AND month = 7 AND day = 28 AND duration < 60);


-- Name of the city thief escaped to
SELECT city FROM airports
    JOIN flights ON flights.destination_airport_id = airports.id
    WHERE origin_airport_id IN (SELECT origin_airport_id FROM flights
        JOIN airports ON airports.id = flights.origin_airport_id
        WHERE city LIKE 'fiftyville' AND year = 2021 AND month = 7 AND day = 29)
    AND year = 2021 AND month = 7 AND day = 29 AND hour = 8;