# in included-file.coffee:
someVar = ...
exports.someVar = someVar

# in main.coffee:
someVar = require('included-file.coffee').someVar

