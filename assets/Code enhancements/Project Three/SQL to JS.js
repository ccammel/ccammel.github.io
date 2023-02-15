// Use the database "messaging"
db = db.getSiblingDB("messaging");

// Insert a person into the "person" collection
db.person.insertOne({
first_name: "Christopher",
last_name: "Cammel"
});

// Add a screen_name field to the person collection
db.person.updateMany({}, {$set: {screen_name: null}});
db.person.updateOne({person_id: 1}, {$set: {screen_name: "flying_fish"}});
db.person.updateOne({person_id: 2}, {$set: {screen_name: "dolphin_gurl"}});
db.person.updateOne({person_id: 3}, {$set: {screen_name: "zoomzoom"}});
db.person.updateOne({person_id: 4}, {$set: {screen_name: "chiken_legz"}});
db.person.updateOne({person_id: 5}, {$set: {screen_name: "KDWarrior"}});
db.person.updateOne({person_id: 6}, {$set: {screen_name: "White_Mamba"}});
db.person.updateOne({person_id: 7}, {$set: {screen_name: "grill_sgt"}});

// Delete a person
db.person.deleteOne({first_name: "Diana", last_name: "Taurasi"});

// Add a favorites field to the contact_list collection
db.contact_list.updateMany({}, {$set: {favorites: null}});
db.contact_list.updateOne({contact_id: 1}, {$set: {favorites: "y"}});
db.contact_list.updateMany({contact_id: {$ne: 1}}, {$set: {favorites: "n"}});

// Insert into contact_list
db.contact_list.insertMany([
{person_id: 7, contact_id: 1},
{person_id: 7, contact_id: 4},
{person_id: 2, contact_id: 5}
]);

// Create the image and message_image collections
db.createCollection("image");
db.createCollection("message_image");

// Insert into image
db.image.insertMany([
{image_name: "Elephant Herd", image_location: "Kenya Nature Preserve"},
{image_name: "Maui", image_location: "Hawaiian Islands, Pacific Ocean"},
{image_name: "Notre Dame Cathedral", image_location: "Paris, France"},
{image_name: "Fenway Park", image_location: "Boston, Massachusetts"},
{image_name: "Selfie Cause I Can", image_location: "Seattle, Washington"}
]);

// Insert into message_image
db.message_image.insertMany([
{message_id: 1, image_id: 5},
{message_id: 1, image_id: 4},
{message_id: 3, image_id: 2},
{message_id: 2, image_id: 3},
{message_id: 4, image_id: 1}
]);

// Find a sender
db.person.find({first_name: "Michael"}).forEach(function(sender) {
    // Join message collection with sender
    db.message.aggregate([{
        $lookup: {
            from: "person",
            localField: "sender_id",
            foreignField: "person_id",
            as: "sender"
        }
    },{
        $unwind: "$sender"
    },{
        $match: {
            "sender.first_name": "Michael"
        }
    },{
        $lookup: {
            from: "person",
            localField: "receiver_id",
            foreignField: "person_id",
            as: "receiver"
        }
    },{
        $unwind: "$receiver"
    }]).forEach(function(joinedMessage) {
    // Project desired fields
        var result = {
            send_first: joinedMessage.sender.first_name,
            send_last: joinedMessage.sender.last_name,
            receive_first: joinedMessage.receiver.first_name,
            receive_last: joinedMessage.receiver.last_name,
            message_id: joinedMessage.message_id,
            message: joinedMessage.message,
            message_timestamp: joinedMessage.send_datetime
        };
        print(tojson(result));
    });
});
    
// Count messages by sender
db.message.aggregate([{
    $lookup: {
        from: "person",
        localField: "sender_id",
        foreignField: "person_id",
        as: "sender"
    }
},{
    $unwind: "$sender"
},{
    $group: {
        _id: "$sender_id",
        message_count: {
            $sum: 1
        },
        first_name: {
            $first: "$sender.first_name"
        },
        last_name: {
            $first: "$sender.last_name"
        },
        person_id: {
            $first: "$sender.person_id"
        }
    }
}]).forEach(function(grouped) {
// Project desired fields
    var result = {
        message_count: grouped.message_count,
        person_id: grouped.person_id,
        first_name: grouped.first_name,
        last_name: grouped.last_name
    };
    print(tojson(result));
});

// Find messages with images
db.message.aggregate([{
    $lookup: {
        from: "message_image",
        localField: "message_id",
        foreignField: "message_id",
        as: "message_image"
    }
},{
    $unwind: "$message_image"
},{
    $lookup: {
        from: "image",
        localField: "message_image.image_id",
        foreignField: "image_id",
        as: "image"
    }
}])