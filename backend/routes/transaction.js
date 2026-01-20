const express = require('express');
const router = express.Router();
const transaction = require('../models/transaction_model');

router.get('/', function(request, response){
    transaction.getAll(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    })
});

router.get('/:idtransaction', function(request, response){
    transaction.getOne(request.params.idtransaction, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    })
});

router.post('/', function(request, response){
    transaction.add(request.body, function(err,result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    })
});

router.delete('/:idtransaction', function(request, response){
    transaction.delete(request.params.idtransaction, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            console.log(result);
            response.send(result);
        }
    })
});

module.exports = router;