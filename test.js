console.log('hier kommt unser neues modul')

var gg = require('./build/Release/GrumpyGolem');
var util = require('util');

x = new gg.mat("2 2 1; 2 3 1; 4 2 4");
// x.fill(2.2);
// = x.n_rows();
// console.log(y);
x.print();
// console.log("___________________________")

x.print();
//x.eye(8,8);
y = x.i();
y.print();
// setTimeout(x.print(),2000);


console.log(util.inspect(x));

x.print();


