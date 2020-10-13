FROM gcc:10
WORKDIR ./
COPY ./* ./
RUN gcc -o compiler compiler.c
RUN chmod +x compiler