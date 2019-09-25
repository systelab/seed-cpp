# Web Server Certificates

The web server used by `seed-cpp` provides HTTPS support. That implies that some certificates need to be provided to set up properly the server.

## Certificates generation

Certificates are generated using `OpenSSL command line tool`:

1> Add OpenSSL installation folder (`%OPENSSLDIR%`) in your `PATH` environment variable.

2> Define an environment variable that points to the OpenSSL configuration file:

```shell
set OPENSSL_CONF=%OPENSSLDIR%/bin/openssl.cnf 
```

3> Generate *key.pem file*:

```shell
%OPENSSLDIR%/bin/openssl genrsa -out key.pem 2048
```

4> Generate *cert.csr*:

```shell
%OPENSSLDIR%/bin/openssl req -new -sha256 -key key.pem -out cert.csr -subj "/C=GB/ST=Barcelona/L=Barcelona/O=Global Security/OU=IT Department/CN=werfen.com\"
```

5> Check *cert.csr* has been generated successfully:

```shell
%OPENSSLDIR%/bin/openssl req -in cert.csr -noout -text
```

6> Generate *cert.crt*:

```shell
%OPENSSLDIR%/bin/openssl x509 -req -days 3650 -in cert.csr -signkey key.pem -out cert.crt
```

7> Generate dhparam.pem file

```shell
%OPENSSLDIR%/bin/openssl.cnf & $(SolutionDir)../lib/openssl/bin/openssl dhparam -out dhparam.pem 1024
```
