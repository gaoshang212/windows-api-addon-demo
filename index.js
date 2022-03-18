const winApi = require('./build/Release/libWinApi.node');

module.exports.EnumWindowsAll = function () {
    return winApi.EnumWindows();
};