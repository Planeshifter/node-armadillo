console.log('hier kommt unser neues modul')

var gg = require('./build/Release/armadillo');
var util = require('util');

x = new gg.mat("2 2 1; 2 3 2; 4 2 4");
y = new gg.mat("1 1 2; 3 2 3; 2 4 2")
//x.print();
//x.shed_col(1);
//x.shed_rows(0,1);
//if (x.is_colvec()===true){console.log("JA")}
//else {console.log("NEIN")};

// var myVec = new gg.vec();

// vec.print();

var z = new gg.Colvec(5);
var r = new gg.Rowvec(3);

x.print();

var t = gg.max(x,y);

t.print();


//z.randn();

//z2 = gg.exp(z)

//z.print();
//z2.print();

x.randn()
//x.print();
x3 = gg.sign(x);
//x3.print();

//console.log(gg.det(x3))


//y = new gg.mat("2 2 1; 2 3 1; 4 2 4");
//z = x.subtract(y);
//x.print();
//x.randn();
// x.fill(2.2);
// = x.n_rows();
// console.log(x.n_elem());
// x.print();
// console.log("___________________________")

// x.print();
//x.eye(8,8);
//y = x.i();
//console.log(x.at(2,2));
// setTimeout(x.print(),2000);

//y2 = gg.chol(x);

//r = new gg.mat();
//q = new gg.mat();

//gg.qr(q,r,x);
//q.print();
//r.print();

//x.print();

//gg.pinv(x);

//x.print();


//console.log(util.inspect(x));

//x.print();
//console.log(x.nrow);


