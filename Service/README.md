This is where the service goes.

# Service
To build the service:
    * Build the project with dotnet.
     docker run --rm -v $(pwd):/app -w /app mcr.microsoft.com/dotnet/sdk:8.0 dotnet publish -c Release -o out

    * Build the docker image
     sudo docker build -t ddmipz/rpc-service .

    * Run it
     sudo docker run -p 5249:8080 ddmipz/rpc-service