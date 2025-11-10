DOCKER_IMAGE := nginx-wasm

build:
	docker build -t $(DOCKER_IMAGE) . --no-cache

run: build
	docker rm -f $(DOCKER_IMAGE)
	docker run --name $(DOCKER_IMAGE) -v `pwd`:/usr/share/nginx/html -it -p 11180:80 --rm $(DOCKER_IMAGE)


karel-invalidate-cache:
	@if [ -z "$(DIST_ID)" ]; then \
		echo "Error: DIST_ID is required. Usage: make karel-invalidate-cache DIST_ID=your-distribution-id"; \
		exit 1; \
	fi
	aws cloudfront create-invalidation \
		--distribution-id $(DIST_ID) \
		--paths "/karel/karel.h"