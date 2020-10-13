FROM g++:8.1.0
WORKDIR ./
COPY ./* ./
RUN g++ -o compiler compiler.cpp 
RUN chmod +x compiler