# BestZappy

A school project to build an autonomous video game through AI clients connecting to a central server orchestrating the game.
## Server

### Deployment

```bash
docker-compose up -d
```

Edit parameters in [`./docker-compose.yml`](docker-compose.yml) !
### Developement install

Please install the dependencies :

```bash
apt install g++ qt5-default make -y
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

### Quick run

```bash
docker-compose up -d
```

### Developement install

```bash
apt install g++ qt5-default make -y
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
