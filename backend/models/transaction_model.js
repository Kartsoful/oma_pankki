const db = require('../database');

const transaction = {
    getAll:function(callback){
        db.query ("SELECT * FROM transaction", callback);
    },

    getOne:function(idtransaction, callback){
        db.query ("SELECT * FROM transaction WHERE idtransaction=?",[idtransaction], callback);
    },

    add:function(transaction, callback) {
        db.query ("INSERT INTO transaction (idaccount, amount, description) VALUES(?,?,?)", [transaction.idaccount, transaction.amount, transaction.description], callback);
    },

    delete:function(idtransaction, callback){
        db.query ("DELETE FROM transaction WHERE idtransaction=?",[idtransaction],callback);
    }
}

module.exports = transaction;