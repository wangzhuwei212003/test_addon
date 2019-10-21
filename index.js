const testAddon = require('./build/Release/testaddon.node');

console.log('addon', testAddon);
console.log('addon', testAddon.hello());
console.log('add', testAddon.add(5, 10));

module.exports = testAddon;