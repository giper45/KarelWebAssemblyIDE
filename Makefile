DOCKER_IMAGE := nginx-wasm

build:
	docker build -t $(DOCKER_IMAGE) . --no-cache

run: build
	docker rm -f $(DOCKER_IMAGE)
	docker run --name $(DOCKER_IMAGE) -v `pwd`:/usr/share/nginx/html -it -p 11180:80 --rm $(DOCKER_IMAGE)
