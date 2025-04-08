FROM debian:12-slim

WORKDIR /usr/src/app

RUN apt-get update && apt-get install -y gcc libcriterion-dev inotify-tools build-essential

COPY . /usr/src/app

COPY ./entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

CMD ["tail", "-f", "/dev/null"]