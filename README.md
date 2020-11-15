# BestZappy

## Server

### Install

Please install the dependencies :

```bash
apt install g++ qt5-default -y
```

**We recommend using QtCreator to build this project.** However, if you wish to use a Makefile, run the following :

```bash
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
```

**We recommend using QtCreator to build this project.** However, if you wish to use a Makefile, run the following :

```bash
cd client/build
make
```

### Run

```bash
cd client/build
./client --host <host> --port <port>
```
