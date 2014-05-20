var bindings = require('bindings')('armadillo.node');

module.exports.mat = function(args)
  {
  return new bindings.mat(args)
  };