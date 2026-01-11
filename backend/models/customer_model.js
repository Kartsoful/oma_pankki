const db = require('../database');

const customer = {
    getAll:function(callback){
        return db.query("SELECT * FROM customer", callback);
    }
}

module.exports = customer;