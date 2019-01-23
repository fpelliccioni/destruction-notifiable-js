# destruction-notifiable-js

NodeJS destruction notifiable types (N-API).


## Usage:

```javascript
// test.js
var dn = require('destruction-notifiable');

function forceGC() {
    if (global.gc) {
        global.gc();
    } else {
        console.warn('No GC hook! Start your program as `node --expose-gc ./test.js`.');
    }
}

function test() {
    var obj = new dn.Destructible(42, function(id) {
        console.log("object destructed " + id);
    });
}

test();
forceGC();
```

### Run: 

`node --expose-gc ./test.js`

### Expected output: 

`object destructed 42`