const mysql = require('mysql2');
const dotnev = require ('dotenv');
dotnev.config();
const connection = mysql.createPool(process.env.SQL_SERVER);

module.exports = connection;