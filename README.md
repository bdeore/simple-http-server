## Simple Multi-Threaded HTTP server

this http server supports a small subset of the HTTP standard. content from www/ directory is served for GET/ requests. all the prevalent MIME types are supported. basic set of headers are transmitted back to the client. command line output indicates resource accessed, ip address : port number of client and access count for the resource.   

### to run the server: 

``
make start
``

### to restart server(and rebuild):

``
make restart
``

### server should be running on:

``
http://[localhost]:[port]/
``

port will be printed out when the server start.


### to test from other remote server:

``
wget [localhost]/sample.html
``


