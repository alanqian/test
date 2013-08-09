var empty = {};
var flight = {
    airline: "Oceanic",
    departure: {
        IATA: "SYD",
        city: "LA",
        time: "2012-12-20 11:30am"
    }
};

document.writeln('hello, world!');
document.writeln(typeof(null));
document.writeln(flight.airline);

document.writeln("**Chapter 4. Functions**");

var add = function(a, b) {
    return a + b;
};

document.writeln("* The function invocation pattern *");
var sum = add(3, 4);
document.writeln("function(a,b): sum=" + sum);


var myObject = {
    value: 0,
    increment: function(inc) {
        this.value += typeof inc === 'number' ? inc : 1;
    }
};
document.writeln("object.function(inc)");

myObject.double = function() {
    var that = this;
    var helper = function() {
        that.value = add(that.value, that.value);
    }
    helper();
};
myObject.increment();
document.writeln(myObject.value); 
myObject.increment(2);
document.writeln(myObject.value); 

document.writeln("value: " + myObject.value); 
myObject.double();
document.writeln("Double(): " + myObject.value); 

document.writeln("* The constructor invocation pattern *");

var Quo = function(string) {
    this.status = string;
};

// add a method named get_status
Quo.prototype.get_status = function() {
    return this.status;
};

// this pattern isn't be recommended
var myQuo = new Quo("confused");
document.writeln(myQuo.get_status());


document.writeln("* The apply invocation pattern *");

var array = [3, 4];
var sum = add.apply(null, array);
document.writeln("sum:" + sum);

var statusObject = {
    status: "A-OK",
};

var status = Quo.prototype.get_status.apply(statusObject);
document.writeln("status:" + status);

// arguments
var sum = function() {
    var i, sum = 0;
    for (i = 0; i < arguments.length; i++) {
        sum += arguments[i];
    }
    return sum;
};
document.writeln("sum: " + sum(2, 3, 4, 5));

document.writeln("* add methods to an exist type *");
Function.prototype.method = function(name, func) {
    if (!this.prototype[name]) {
        this.prototype[name] = func;
    }
    return this;
};

Number.method('integer', function() {
    return Math[this < 0 ? 'ceil' : 'floor'](this);
});

document.writeln("integer():" + (-10/3).integer());

// for in: all
// this: hasOwnProperty

var fade = function (node) {
    var level = 1;
    var step = function() {
        var hex = level.toString(16);
        node.style.backgroundColor = ' #FFFF' + hex; // + hex;
        if (level < 255) {
            level += 1;
            setTimeout(step, 100);
        }
    }
    setTimeout(step, 100);
};
document.writeln("Closure: fade()");
fade(document.body);

String.method('deentityify', function () {
    var entity = {
        quot: '"',
        lt: '<',
        gt: '>',
    };
    var that = this;
    return function() {
        return that.replace(/&([^&;]+);/g,
        function (a, b) {
            var r = entity[b];
            console.log(arguments);
            return typeof r === 'string' ? r : a;
        });
    }();});

document.writeln("Module:");
document.writeln('&lt;&quot;&gt;'.deentityify()); // '<">'

