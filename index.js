var binary = require('node-pre-gyp');
var path = require('path')
var dn_path = binary.find(path.resolve(path.join(__dirname,'./package.json')));

// console.log(`dn_path: ${dn_path}`)
var dn = require(dn_path);
// require('assert').equal(dn.hello(),"hello");

// ---------------------------------------------

// var dn = require('bindings')('destruction-notifiable');

// ---------------------------------------------

module.exports = dn;
