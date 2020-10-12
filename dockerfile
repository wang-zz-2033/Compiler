FROM gcc:10
WORKDIR ./
COPY ./* ./
RUN gcc compiler.c -o compiler
RUN chmod +x compiler