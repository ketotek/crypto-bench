
#include <fcntl.h>

#include "af_alg.h"

bool AF_ALGTest::do_operation(int op, int rounds)
{
	int tfmfd, opfd;
	struct sockaddr_alg sa = {
		.salg_family = AF_ALG
	};
	struct msghdr msg = {};
	struct iovec iov;
	int pipes[2];
	struct cmsghdr *cmsg;
	char cbuf[CMSG_SPACE(4) + CMSG_SPACE(12)] = {};
	struct af_alg_iv *iv;
	int rc, i;
	ssize_t r;

	strcpy((char*)sa.salg_type, "skcipher");
	strcpy((char*)sa.salg_name, "cbc(cast5)");

	tfmfd = socket(AF_ALG, SOCK_SEQPACKET, 0);
	assert(tfmfd >= 0);

	rc = bind(tfmfd, (struct sockaddr *)&sa, sizeof(sa));
	assert(rc == 0);

	rc = setsockopt(tfmfd, SOL_ALG, ALG_SET_KEY,
		   "\x06\xa9\x21\x40\x36\xb8\xa1\x5b"
		   "\x51\x2e\x03\xd5\x34\x12\x00\x06", 8);
	assert(rc == 0);

	opfd = accept(tfmfd, NULL, 0);
	assert(opfd != -1);

	msg.msg_control = cbuf;
	msg.msg_controllen = sizeof(cbuf);

	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_level = SOL_ALG;
	cmsg->cmsg_type = ALG_SET_OP;
	cmsg->cmsg_len = CMSG_LEN(4);
	*(__u32 *)CMSG_DATA(cmsg) = op;

	cmsg = CMSG_NXTHDR(&msg, cmsg);
	cmsg->cmsg_level = SOL_ALG;
	cmsg->cmsg_type = ALG_SET_IV;
	cmsg->cmsg_len = CMSG_LEN(12);
	iv = (af_alg_iv*)CMSG_DATA(cmsg);
	iv->ivlen = 8;
	memcpy(iv->iv, "\x3d\xaf\xba\x42\x9d\x9e\xb4\x30"
		       "\xb4\x22\xda\x80\x2c\x9f\xac\x41", 8);

#if 1
	iov.iov_base = &in[0];
	iov.iov_len = data_size();

	msg.msg_iovlen = 1;
	msg.msg_iov = &iov;
#endif
#if 0
	iov.iov_base = in; 
	iov.iov_len = 4096; 

	msg.msg_iovlen = 0; 
	msg.msg_flags = MSG_MORE; 
	//msg.msg_iov = &iov;

	pipe(pipes);
#endif
	for (i = 0; i < rounds; i++) {
		r = sendmsg(opfd, &msg, 0);
		if (r < 0) {
			perror("sendmsg");
			return false;
		}
		//read(opfd, out, data_size());
 #if 0
		vmsplice(pipes[1], &iov, 1, SPLICE_F_GIFT); 
		splice(pipes[0], NULL, opfd, NULL, 4096, 0); 
#endif
		read(opfd, out, 4096); 

	}


	return true;
}


