# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2012 Spectra Logic.  All rights reserved.
# Use is subject to license terms.
#


atf_test_case cifs_attr_001_pos cleanup
cifs_attr_001_pos_head()
{
	atf_set "descr" "Verify set/clear DOS attributes will succeed while user haswrite_attributes permission or PRIV_FILE_OWNER privilege"
	atf_set "require.config" "zfs_acl zfs_xattr"
	atf_set "require.progs" "ksh93 runwattr"
}
cifs_attr_001_pos_body()
{
	. $(atf_get_srcdir)/../../../include/default.cfg
	. $(atf_get_srcdir)/cifs.kshlib
	. $(atf_get_srcdir)/../acl.cfg

	verify_disk_count "$DISKS" 1
	ksh93 $(atf_get_srcdir)/../setup.ksh || atf_fail "Setup failed"
	ksh93 $(atf_get_srcdir)/cifs_attr_001_pos.ksh || atf_fail "Testcase failed"
}
cifs_attr_001_pos_cleanup()
{
	. $(atf_get_srcdir)/../../../include/default.cfg
	. $(atf_get_srcdir)/cifs.kshlib
	. $(atf_get_srcdir)/../acl.cfg

	ksh93 $(atf_get_srcdir)/../cleanup.ksh || atf_fail "Cleanup failed"
}


atf_test_case cifs_attr_002_pos cleanup
cifs_attr_002_pos_head()
{
	atf_set "descr" "Verify set/clear BSD'ish attributes will succeed while user hasPRIV_FILE_FLAG_SET/PRIV_FILE_FLAG_CLEAR privilege"
	atf_set "require.config" "zfs_acl zfs_xattr"
	atf_set "require.progs" "ksh93 runwattr"
}
cifs_attr_002_pos_body()
{
	. $(atf_get_srcdir)/../../../include/default.cfg
	. $(atf_get_srcdir)/cifs.kshlib
	. $(atf_get_srcdir)/../acl.cfg

	verify_disk_count "$DISKS" 1
	ksh93 $(atf_get_srcdir)/../setup.ksh || atf_fail "Setup failed"
	ksh93 $(atf_get_srcdir)/cifs_attr_002_pos.ksh || atf_fail "Testcase failed"
}
cifs_attr_002_pos_cleanup()
{
	. $(atf_get_srcdir)/../../../include/default.cfg
	. $(atf_get_srcdir)/cifs.kshlib
	. $(atf_get_srcdir)/../acl.cfg

	ksh93 $(atf_get_srcdir)/../cleanup.ksh || atf_fail "Cleanup failed"
}


atf_test_case cifs_attr_003_pos cleanup
cifs_attr_003_pos_head()
{
	atf_set "descr" "Verify DOS & BSD'ish attributes will provide theaccess limitation as expected."
	atf_set "require.config" "zfs_acl zfs_xattr"
	atf_set "require.progs" "ksh93 runat"
}
cifs_attr_003_pos_body()
{
	. $(atf_get_srcdir)/../../../include/default.cfg
	. $(atf_get_srcdir)/cifs.kshlib
	. $(atf_get_srcdir)/../acl.cfg

	verify_disk_count "$DISKS" 1
	ksh93 $(atf_get_srcdir)/../setup.ksh || atf_fail "Setup failed"
	ksh93 $(atf_get_srcdir)/cifs_attr_003_pos.ksh || atf_fail "Testcase failed"
}
cifs_attr_003_pos_cleanup()
{
	. $(atf_get_srcdir)/../../../include/default.cfg
	. $(atf_get_srcdir)/cifs.kshlib
	. $(atf_get_srcdir)/../acl.cfg

	ksh93 $(atf_get_srcdir)/../cleanup.ksh || atf_fail "Cleanup failed"
}


atf_init_test_cases()
{

	atf_add_test_case cifs_attr_001_pos
	atf_add_test_case cifs_attr_002_pos
	atf_add_test_case cifs_attr_003_pos
}
