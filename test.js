console.log('hier kommt unser neues modul')

var gg = require('./build/Release/GrumpyGolem');
var util = require('util');

x = new gg.mat("2 2; 2 3; 4 2");
// x.fill(2.2);
// = x.n_rows();
// console.log(y);
// x.print();
// console.log("___________________________")

y = x.t();
y.print();
x.print();

// setTimeout(x.print(),2000);

// console.log(x.n_rows());
// console.log(util.inspect(x));