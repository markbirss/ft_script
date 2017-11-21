
// static void test(int fdm, int fds, int fdf, t_env *env)
// {
// 	int pid;
// 	int i;
// 	fd_set set;
// 	char buf[64];

// 	if ((pid = fork()) < 0)
// 		exit(2);
// 	if (!pid)
// 	{
// 		close(fdm);
// 		dup2(fds, 0);
// 		dup2(fds, 1);
// 		dup2(fds, 2);
// 		execl(env->command[0], env->command[0]);
// 		exit(3);
// 	}
// 	/* father: copy stdin/out to/from master */
// 	close(fds);
// 	system("stty raw -echo");//avoid echo command
// 	FD_ZERO(&set);
// 	while (waitpid(pid, &i, WNOHANG) != pid)
// 	{
// 		FD_SET(0, &set);
// 		FD_SET(fdm, &set);
// 		select(fdm + 1, &set, NULL, NULL, NULL);
// 		if (FD_ISSET(0, &set))
// 		{
// 			i = read(0, buf, 64);
// 			if (i > 0)
// 				write(fdm, buf, i);
// 		}
// 		if (FD_ISSET(fdm, &set))
// 		{
// 			i = read(fdm, buf, 64);
// 			if (i > 0)
// 			{
// 				write(1, buf, i);
// 				write(fdf, buf, i);
// 			}
// 		}
// 	}
// 	system("stty sane");
// 	exit(0);
// }