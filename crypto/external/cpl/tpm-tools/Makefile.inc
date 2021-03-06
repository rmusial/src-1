# $NetBSD: Makefile.inc,v 1.1 2012/01/28 16:04:12 christos Exp $

.include <bsd.own.mk>

TPM_TOOLS=${NETBSDSRCDIR}/crypto/external/cpl/tpm-tools
DIST=${TPM_TOOLS}/dist

CPPFLAGS+= -I${TPM_TOOLS}/include -I${DIST}/include
CPPFLAGS+= -DHAVE_CONFIG_H -D_LINUX -DTSS_LIB_IS_12
