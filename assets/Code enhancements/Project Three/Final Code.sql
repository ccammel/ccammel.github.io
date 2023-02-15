USE messaging;

INSERT INTO messaging.person (first_name, last_name)
VALUES ("Christopher", "Cammel");

ALTER TABLE messaging.person
ADD screen_name VARCHAR(25) NOT NULL;

UPDATE person
SET screen_name = "flying_fish"
WHERE person_id = 1;

UPDATE person
SET screen_name = "dolphin_gurl"
WHERE person_id = 2;

UPDATE person
SET screen_name = "zoomzoom"
WHERE person_id = 3;

UPDATE person
SET screen_name = "chiken_legz"
WHERE person_id = 4;

UPDATE person
SET screen_name = "KDWarrior"
WHERE person_id = 5;

UPDATE person
SET screen_name = "White_Mamba"
WHERE person_id = 6;

UPDATE person 
SET screen_name = "sea_grill_sgt"
WHERE person_id = 7;

DELETE FROM person WHERE first_name = "Diana" AND last_name = "Taurasi";

ALTER TABLE messaging.contact_list
ADD favorites VARCHAR(10) NULL;

UPDATE contact_list
SET favorites = "y";

UPDATE contact_list
SET favorites = "n"
WHERE contact_id <> 1;

INSERT INTO messaging.contact_list (person_id, contact_id)
  VALUES (7, 1),
  (7, 4),
  (2, 5);
  
UPDATE contact_list
SET favorites = "y";

UPDATE contact_list
SET favorites = "n"
WHERE contact_id <> 1;

CREATE TABLE image (
  image_id INT(8) NOT NULL auto_increment,
  image_name VARCHAR(50) NOT NULL,
  image_location VARCHAR(250) NOT NULL,
PRIMARY KEY(image_id)
) AUTO_INCREMENT=1;

CREATE TABLE message_image (
  message_id INT(8) NOT NULL,
  image_id INT(8) NOT NULL,
PRIMARY KEY(message_id, image_id),
FOREIGN KEY(message_id) REFERENCES message(message_id),
FOREIGN KEY(image_id) REFERENCES image(image_id)
);

INSERT INTO messaging.image (image_name, image_location)
  VALUES ("Elephant Herd", "Kenya Nature Preserve"),
  ("Maui", "Hawaiian Islands, Pacific Ocean"),
  ("Notre Dame Cathedral", "Paris, France"),
  ("Fenway Park", "Boston, Massachusetts"),
  ("Selfie Cause I Can", "Seattle, Washington");
  
INSERT INTO message_image (message_id, image_id)
  VALUES (1, 5),
  (1, 4),
  (3, 2),
  (2, 3),
  (4, 1);
  
SELECT
sender.first_name AS send_first,
sender.last_name AS send_last,
receiver.first_name AS receive_first,
receiver.last_name AS receive_last,
message.message_id, message,
message.send_datetime AS message_timestamp
FROM person AS sender
JOIN message
  ON sender.person_id = message.sender_id
JOIN person AS receiver
  ON message.receiver_id = receiver.person_id
WHERE UPPER(sender.first_name) = "Michael";

SELECT
COUNT(message.message_id) AS message_count
person.person_id, first_name, last_name
FROM message
JOIN person
  ON message.sender_id = person.person_id
GROUP BY message.sender_id;

SELECT
message.message_id,
message.message,
message.send_datetime AS message_timestamp,
image.image_name AS first_image_name,
image.image_location AS first_image_location
FROM message
INNER JOIN message_image
  ON message.message_id = message_image.message_id
INNER JOIN image
  ON message_image.image_id = image.image_id
GROUP BY message.message_id;