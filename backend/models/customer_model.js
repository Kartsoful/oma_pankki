const db = require('../database');

const customer = {
    getAll:function(callback){
        return db.query("SELECT * FROM customer", callback);
    },

    getOne:function(idcustomer, callback){
        return db.query("SELECT * FROM customer WHERE idcustomer=?",[idcustomer], callback);
    },

    add:function(customer, callback){
        return db.query("INSERT INTO customer (fname, lname, street_address, city) VALUES(?,?,?,?)",[customer.fname,customer.lname,customer.street_address,customer.city],callback);
    },

    update:function(customer, idcustomer, callback){
        console.log(customer);
        console.log(idcustomer);
        return db.query("UPDATE customer SET fname=?,lname=?,street_address=?,city=? WHERE idcustomer=?",[customer.fname,customer.lname,customer.street_address,customer.city,idcustomer],callback);
    },

    delete:function(idcustomer, callback){
        return db.query("DELETE FROM customer WHERE idcustomer=?",[idcustomer],callback);
    }
}

module.exports = customer;