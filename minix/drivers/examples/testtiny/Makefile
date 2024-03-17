PROG=	testtiny
SRCS=	testtiny.cc

FILES=${PROG}.conf
FILESNAME=${PROG}
FILESDIR= /system.conf.d

DADD+= ${LIBTINYKIT} ${LIBSYS}
LDADD+= -ltinykit -lsys

.include <minix.service.mk>
