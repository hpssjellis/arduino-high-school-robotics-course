var http = require('http');


function myHandler(req, res) {
    var POST = {};
    if (req.method == 'POST') {
        req.on('data', function(data) {
            data = data.toString();
            data = data.split('&');
            for (var i = 0; i < data.length; i++) {
                var _data = data[i].split("=");
                POST[_data[0]] = _data[1];
            }
            console.log(POST);
        })
    }
}




    var server = http.createServer ( function(request,response){

    response.writeHead(200,{"Content-Type":"text\plain"});
    if(request.method == "GET")
        {
            response.end("received GET request cool.");
            console.log('A GET was received');
        }
    else if(request.method == "POST")
        {
            response.end("received POST request.");
            console.log('A POST was received');
            myHandler(request,response);
           // console.log(request);
        }
    else
        {
            response.end("Undefined request .");
            console.log('nothing');
        }
});

server.listen(8000);
console.log("Server running on port 8000");
