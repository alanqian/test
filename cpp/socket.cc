udp server:

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

	while ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
		(struct sockaddr *)&their_addr, &addr_len)) == -1) 
    {
        // handle mesgs here
        // ...
    }

    close(sockfd);


udp client:

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sendto(sockfd, argv[2], strlen(argv[2]), 0,
			 (struct sockaddr *)&their_addr, sizeof their_addr);
    // ...

	close(sockfd);


tcp server:

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr);
	listen(sockfd, BACKLOG);

	sigaction(SIGCHLD, &sa, NULL);

	while(1) 
    {  // main accept() loop
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		
			if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
		close(new_fd);  // parent doesn't need this
	}

    close(sockfd);

tcp client:

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	connect(sockfd, (struct sockaddr *)&their_addr, sizeof their_addr);

	numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0);

	close(sockfd);

