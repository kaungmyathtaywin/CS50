-- Select description from the day of thef on Chamberlin Street
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";

-- Select transcripts from interviews that happened on the same day
SELECT transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%";

-- Select exiting cars from parking lot between 10:15 and 10:25
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;

-- Select bank accounts which were being withdrawed on the same day on Fifer street
SELECT * FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";

-- Select calls that took last then a minute on the same day
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

-- Select the earliest flight leaving Fiftyville on the next day
SELECT * FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2020 AND month = 7 AND day = 29
ORDER BY hour LIMIT 1;

-- Select passengers on the earliest flight
SELECT * FROM passengers WHERE flight_id = 
(SELECT flights.id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2020 AND month = 7 AND day = 29
ORDER BY hour LIMIT 1);

-- Select each passenger info from people table
SELECT * FROM people WHERE passport_number IN 
(
    SELECT passport_number FROM passengers WHERE flight_id = 
    (
        SELECT flights.id FROM flights
        JOIN airports ON flights.origin_airport_id = airports.id
        WHERE year = 2020 AND month = 7 AND day = 29
        ORDER BY hour LIMIT 1
    )
);

-- Select passenger names whose cars exit on the same time from courthouse at the time of theft
SELECT name FROM
(
    SELECT * FROM people WHERE passport_number IN 
    (
        SELECT passport_number FROM passengers WHERE flight_id = 
        (
            SELECT flights.id FROM flights
            JOIN airports ON flights.origin_airport_id = airports.id
            WHERE year = 2020 AND month = 7 AND day = 29
            ORDER BY hour LIMIT 1
        )
    )
) AS Airplane 
JOIN 
(
    SELECT * FROM courthouse_security_logs 
    WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute 
    BETWEEN 15 AND 25
) AS Courthouse
ON Airplane.license_plate = Courthouse.license_plate;
--> Ernest, Danielle, Roger, Evelyn

-- Select calls that were made by Ernest, Danielle , Roger, Evelyn on the day of theft which took less than a minute
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND 
caller IN ("(367) 555-5533", "(389) 555-5198", "(130) 555-0289", "(499) 555-9472");
--> (130) 555-0289, (499) 555-9472, (367) 555-5533

-- Select name of the caller 
SELECT name FROM people WHERE phone_number IN ("(130) 555-0289", "(499) 555-9472", "(367) 555-5533");
--> Roger, Evelyn, Ernest

-- Select bank info from the name of callers 
SELECT * FROM people 
JOIN bank_accounts 
ON people.id = bank_accounts.person_id
WHERE name IN ("Roger", "Evelyn", "Ernest");
--> Ernest (Other two don't have bank accounts. So Ernest is the thief because the theif made money withdrawal on ATM)

-- Select departing airport
SELECT * FROM airports WHERE id = 
(SELECT destination_airport_id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2020 AND month = 7 AND day = 29
ORDER BY hour LIMIT 1);
--> Heathrow Airport, London

-- Select name of the person who recieved call from Ernest 
SELECT name FROM people WHERE phone_number = 
(SELECT receiver FROM phone_calls 
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller =  "(367) 555-5533");
--> Berthold