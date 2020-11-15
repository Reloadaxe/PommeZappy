# BestZappy

## Server

### Install

Please install the dependencies and compile the library :

```bash
apt install g++ qt5-default -y
cd server/build
make server
```

### Run

```bash
./server # --help
```

## Client

### Install

```bash
apt install g++ qt5-default -y
cd client/build
make
```

### Run

```bash
cd client/build
./client --host <host> --port <port>
```
