FROM g++:8.1.0
WORKDIR /app/
COPY ./* ./
RUN g++ work.cpp -o work
RUN chmod +x work