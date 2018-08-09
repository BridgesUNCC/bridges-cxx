#!/bin/sh

GITDESC=$(git describe --tags --dirty)
TARGETDIR="bridges-cxx-windows-${GITDESC}"
ZIPFILE="${TARGETDIR}.zip"


if [ -e ${TARGETDIR} ]
then
    echo "remove the build directory with rm -rf ${TARGETDIR}/"
    exit 1
fi


if [ -e ${ZIPFILE} ]
then
    echo "remove the target zipfile ${ZIPFILE}"
    exit 1
fi


mkdir ${TARGETDIR}

RAPIDJSONPATH="dependencies/rapidjson/rapidjson-73063f5002612c6bf64fe24f851cd5cc0d83eef9/"
CURLPATH="dependencies/curl/libcurl-vc-x64-release-dll-ipv6-sspi-winssl"
BRIDGESHEADERPATH="../../src/"

mkdir ${TARGETDIR}/include
mkdir ${TARGETDIR}/lib
mkdir ${TARGETDIR}/bin

TARGETINCLUDE="${TARGETDIR}/include"
TARGETLIB="${TARGETDIR}/lib"
TARGETBIN="${TARGETDIR}/bin"

#copy bridges headers
cp -r ${BRIDGESHEADERPATH}/* ${TARGETINCLUDE}/

#copy rapidjson headers 
cp -r ${RAPIDJSONPATH}/include/* ${TARGETINCLUDE}/

#copy curl headers
cp -r ${CURLPATH}/include/* ${TARGETINCLUDE}/

#copy curl lib
cp -r ${CURLPATH}/lib/* ${TARGETLIB}/

#copy curl bin
cp -r ${CURLPATH}/bin/* ${TARGETBIN}/


zip -r ${ZIPFILE} ${TARGETDIR}


