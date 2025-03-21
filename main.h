#define exit_with_error(reason)                                                           \
                                                                               \
{perror(reason); exit(EXIT_FAILURE);}
