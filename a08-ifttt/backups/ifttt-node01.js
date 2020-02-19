var http = require('http');

let myData;
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
            request.on('data', function(data) {
                myData = data.toString();
               console.log(myData);
            })
           
        }
    else
        {
            response.end("Undefined request .");
            console.log('nothing');
        }
});

server.listen(8000);
console.log("Server running on port 8000");
