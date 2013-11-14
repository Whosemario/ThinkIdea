var io = require("socket.io").listen(8008);

var conns = {};
io.sockets.on('connection', function (socket){
    var cid = socket.id;
    console.log(cid + " connect...");
    for(ccid in conns) {
        var soc = conns[ccid];
        soc.emit('join', {cid: cid});
    }
    socket.emit('join', {cid: cid});
    conns[cid] = socket;

    socket.on('say', function(data) {
        data.cid = cid;
        for (var ccid in conns) {
            var soc = conns[ccid];
            soc.emit('broadcast', data);
        }
    });

    socket.on('disconnect', function() {
        delete conns[cid];
        for(var ccid in conns) {
            var soc = conns[ccid];
            soc.emit('quit', {cid: cid});
        }
    });
});
