FROM gcc:10
WORKDIR ./
COPY ./* ./
RUN gcc -lstdc++ compiler.cpp -o compiler
RUN chmod +x compiler