var dn = require('destruction-notifiable');

function object_destructed(id) {
  console.log("object destructed " + id);
}

function forceGC() {
    if (global.gc) {
        global.gc();
    } else {
        console.warn('No GC hook! Start your program as `node --expose-gc ./tests.js`.');
    }
}

class Destructible2 extends dn.Destructible {
    constructor(id, func, id2) {
        super(id, func);
        this.id2 = id2;
    }
}

class Destructible3 extends dn.Destructible {
    constructor(id, func, func2) {
        super(id, func);
        this.func2 = func2;
    }

    doCallFunc2(x) {
        this.func2(x);
    };
}

function test1() {
    var obj = new dn.Destructible(10, function(id) {
        console.log("object destructed " + id);
      });
}

function test2() {
    var obj = new Destructible2(10, function(id) {
        console.log("object destructed " + id);
      }, 11);
}

function test3() {
    var obj = new dn.Destructible(10, object_destructed);
}

function test4() {

    var arr = [];
    arr.push(new dn.Destructible(1, object_destructed));
    arr.push(new dn.Destructible(2, object_destructed));
    arr.push(new dn.Destructible(3, object_destructed));
    arr.push(new dn.Destructible(4, object_destructed));
    arr.push(new dn.Destructible(5, object_destructed));
    arr.push(new dn.Destructible(6, object_destructed));
    arr.push(new dn.Destructible(7, object_destructed));

    // console.log(obj);
    // console.log(arr[0].value);
    // console.log(arr[0].value);
    // console.log(arr[0].value);
    // console.log(arr[0].value);
    // arr[0].doCall()
    // obj.doCall()

    // delete obj;
    // obj = null;
    // arr = [];
    // arr = null;

    // while(arr.length > 0) {
    //     arr.pop();
    // }
}

function test5() {
    obj_id = 10
    var obj = new dn.Destructible(10, function(id) {
        console.log("object destructed " + obj_id);
      });
}

function test6() {
    var obj = new dn.Destructible(10, function(id) {
        console.log("object destructed " + obj.id);
      });

    // No destruction    
}

function test6a() {
    var obj = new dn.Destructible(10, function(x) {
        console.log(`object destructed: ${this.id}`);
      });
}


function test7() {
    var obj = new dn.Destructible(10, function(id) {
        console.log(`object destructed: ${obj.id}`);
      });

    // No destruction    
}

function test8() {
    var obj = new Destructible3(10, 
        function(id) {
            console.log("object destructed " + id);
        }, 
        function(id) {
            console.log(`doCallFunc2: ${id}`);
        });
}

function test9() {
    var obj = new Destructible3(9, 
        function() {
            console.log("object destructed");
        }, 
        function(id) {
            console.log(`func2 callback: ${obj}`);
        });
    
    // obj.doCall()
    // obj.doCallFunc2(88)
}

function test10() {
    var obj = new Destructible3(10, 
        function(x) {
            console.log("object destructed ");
        }, 
        function(id) {
            console.log(`func2 callback: ${this.id}`);
        });
    
    // obj.doCall()
    obj.doCallFunc2(88)
}

function test11() {
    var obj = new Destructible3(11, object_destructed, 
        function(x) {
            console.log(`func2 callback: ${x} ${obj}`);
        });
    
    // obj.doCallFunc2(88)
}

// test1();
// test2();
// test3();
// test4();
// test5();
// test6();
// test6a();
// test7();
// test8();
// test9();
test10();
// test11();

forceGC();


