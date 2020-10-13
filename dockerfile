FROM gcc:10
WORKDIR ./
COPY ./* ./
RUN gcc -o compiler compiler.cpp -lstdc++
RUN chmod +x compiler