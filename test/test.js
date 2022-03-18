let winApi = require('../');

console.time('EnumWindowsAll');
const list = winApi.EnumWindowsAll()
console.timeEnd('EnumWindowsAll');

console.log(list);

