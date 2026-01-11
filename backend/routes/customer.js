const express = require('express');
const router = express.Router();
const customer = require('../models/customer_model');

router.get('/', function(request, response){
    customer.getAll(function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

router.get('/:idcustomer',function(request,response){
    customer.getOne(request.params.idcustomer, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result)
        }
    })
});

router.post('/', function(request, response){
    customer.update(request.body, request.params.idcustomer, function(err,result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    })
});

router.put('/:idcustomer', function(request,response){
    customer.update(request.body, request.params.idcustomer, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            console.log(result.affectedRows);
            response.json(result);
        }
    })
});

router.delete('/:idcustomer', function(request, response){
    customer.delete(request.params.idcustomer, function(err, result){
        if(err){
            response.send(err);
        } else {
            console.log(result);
            response.json(result);
        }
    })
});

module.exports = router;