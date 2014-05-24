//user.js
var mongodb = require('./db');

function User(user) {
    this.name = user.name;
    this.password = user.password;
    this.gender = user.gender;
    this.interest = user.interest;
    this.firstname = user.firstname;
    this.lastname = user.lastname;
    this.email = user.email;
    this.age = user.age;
    this.zipcode = user.zipcode;
    this.like = user.like;
    this.dontcare = user.dontcare;
    this.dislike = user.dislike;
    this.faceurl = user.faceurl;

};
module.exports = User;

User.prototype.save = function save(callback) {
    var user = {
        name: this.name,
        password: this.password,
    };
    mongodb.open(function (err, db) {
        if (err) {
            return callback(err);
        }

        db.collection('users', function (err, collection) {
            if (err) {
                mongodb.close();
                return callback(err);
            }
            collection.ensureIndex('name', { unique: true });
            collection.insert(user, { safe: true }, function (err, user) {
                mongodb.close();
                callback(err, user);
            });
        });
    });
};

User.updateProfile = function updateProfile(username,userinfo,callback){
    mongodb.open(function(err,db){
        if(err){
            return callback(err);
        }
        db.collection('users',function(err,collection){
            if(err){
                mongodb.close();
                return callback(err);
            }
            console.log('update:' + username);
            console.log('update:' + userinfo.gender);
            console.log('update:' + userinfo.interest);
            collection.update({name:username},{$set:{gender:userinfo.gender,interest:userinfo.interest,like:userinfo.like,dontcare:userinfo.dontcare,dislike:userinfo.dislike,email:userinfo.email,zipcode:userinfo.zipcode,age:userinfo.age}},function(err){
                mongodb.close();
                callback(err);
            })
        })
    })
}

User.updateFace = function updateFace(username,location,callback){
    mongodb.open(function(err,db){
        if(err){
            return callback(err);
        }
        db.collection('users',function(err,collection){
            if(err){
                mongodb.close();
                return callback(err);
            }
            collection.update({name:username},{$set:{faceurl:location}},function(err){
                mongodb.close();
                callback(err);
            })

        })
    })

}
User.get = function get(username, callback) {
    mongodb.open(function (err, db) {
        if (err) {
            return callback(err);
        }
        db.collection('users', function (err, collection) {
            if (err) {
                mongodb.close();
                return callback(err);
            }
            collection.findOne({ name: username }, function (err, doc) {
                mongodb.close();
                if (doc) {
                    var user = new User(doc);
                    callback(err, user);
                } else {
                    callback(err, null);
                }
            });
        });
    });
};
