/**
 * Semver - The Semantic Versioning
 *
 * (c) Axel Etcheverry <axel@etcheverry.biz>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <semver/version.hpp>

BOOST_AUTO_TEST_SUITE(semver_version)

BOOST_AUTO_TEST_CASE(test_simple_version)
{
    semver::version version("1.2.3");

    BOOST_CHECK_EQUAL(version.isValid(), true);
    BOOST_CHECK_EQUAL(version.isStable(), true);
    BOOST_CHECK_EQUAL(version.getVersion(), "1.2.3");
    BOOST_CHECK_EQUAL(version.getMajor(), 1);
    BOOST_CHECK_EQUAL(version.getMinor(), 2);
    BOOST_CHECK_EQUAL(version.getPatch(), 3);
    BOOST_CHECK_EQUAL(version.getPreReleaseType(), semver::PRE_RELEASE_NONE);
    BOOST_CHECK_EQUAL(version.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version.getBuild(), "");

    semver::version version1("0.0.1");

    BOOST_CHECK_EQUAL(version1.isValid(), true);
    BOOST_CHECK_EQUAL(version1.isStable(), false);
    BOOST_CHECK_EQUAL(version1.getVersion(), "0.0.1");
    BOOST_CHECK_EQUAL(version1.getMajor(), 0);
    BOOST_CHECK_EQUAL(version1.getMinor(), 0);
    BOOST_CHECK_EQUAL(version1.getPatch(), 1);
    BOOST_CHECK_EQUAL(version1.getPreReleaseType(), semver::PRE_RELEASE_NONE);
    BOOST_CHECK_EQUAL(version1.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version1.getBuild(), "");
}

BOOST_AUTO_TEST_CASE(test_simple_error_version)
{
    semver::version version("a.b.c");

    BOOST_CHECK_EQUAL(version.isValid(), false);
    BOOST_CHECK_EQUAL(version.getVersion(), "a.b.c");
    BOOST_CHECK_EQUAL(version.getMajor(), 0);
    BOOST_CHECK_EQUAL(version.getMinor(), 0);
    BOOST_CHECK_EQUAL(version.getPatch(), 0);
    BOOST_CHECK_EQUAL(version.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version.getBuild(), "");

    semver::version version1("0.b.c");

    BOOST_CHECK_EQUAL(version1.isValid(), false);
    BOOST_CHECK_EQUAL(version1.getVersion(), "0.b.c");
    BOOST_CHECK_EQUAL(version1.getMajor(), 0);
    BOOST_CHECK_EQUAL(version1.getMinor(), 0);
    BOOST_CHECK_EQUAL(version1.getPatch(), 0);
    BOOST_CHECK_EQUAL(version1.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version1.getBuild(), "");

    semver::version version2("0.1.c");

    BOOST_CHECK_EQUAL(version2.isValid(), false);
    BOOST_CHECK_EQUAL(version2.getVersion(), "0.1.c");
    BOOST_CHECK_EQUAL(version2.getMajor(), 0);
    BOOST_CHECK_EQUAL(version2.getMinor(), 0);
    BOOST_CHECK_EQUAL(version2.getPatch(), 0);
    BOOST_CHECK_EQUAL(version2.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version2.getBuild(), "");

    semver::version version3("0.0.0");

    BOOST_CHECK_EQUAL(version3.isValid(), false);
    BOOST_CHECK_EQUAL(version3.getVersion(), "0.0.0");
    BOOST_CHECK_EQUAL(version3.getMajor(), 0);
    BOOST_CHECK_EQUAL(version3.getMinor(), 0);
    BOOST_CHECK_EQUAL(version3.getPatch(), 0);
    BOOST_CHECK_EQUAL(version3.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version3.getBuild(), "");

    semver::version version4("");

    BOOST_CHECK_EQUAL(version4.isValid(), false);
    BOOST_CHECK_EQUAL(version4.getVersion(), "");
    BOOST_CHECK_EQUAL(version4.getMajor(), 0);
    BOOST_CHECK_EQUAL(version4.getMinor(), 0);
    BOOST_CHECK_EQUAL(version4.getPatch(), 0);
    BOOST_CHECK_EQUAL(version4.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version4.getBuild(), "");
}


BOOST_AUTO_TEST_CASE(test_error_version)
{
    semver::version version("1.0.0-alpha.01");

    BOOST_CHECK_EQUAL(version.isValid(), false);
    BOOST_CHECK_EQUAL(version.getVersion(), "1.0.0-alpha.01");
    BOOST_CHECK_EQUAL(version.getMajor(), 1);
    BOOST_CHECK_EQUAL(version.getMinor(), 0);
    BOOST_CHECK_EQUAL(version.getPatch(), 0);
    BOOST_CHECK_EQUAL(version.getPreRelease(), "alpha.01");
    BOOST_CHECK_EQUAL(version.getBuild(), "");
}

BOOST_AUTO_TEST_CASE(test_pre_release_version)
{
    semver::version version("1.2.3-beta");

    BOOST_CHECK_EQUAL(version.isValid(), true);
    BOOST_CHECK_EQUAL(version.isStable(), false);
    BOOST_CHECK_EQUAL(version.getVersion(), "1.2.3-beta");
    BOOST_CHECK_EQUAL(version.getMajor(), 1);
    BOOST_CHECK_EQUAL(version.getMinor(), 2);
    BOOST_CHECK_EQUAL(version.getPatch(), 3);
    BOOST_CHECK_EQUAL(version.getPreReleaseType(), semver::PRE_RELEASE_BETA);
    BOOST_CHECK_EQUAL(version.getPreRelease(), "beta");
    BOOST_CHECK_EQUAL(version.getBuild(), "");

    semver::version version1("1.0.0-alpha");

    BOOST_CHECK_EQUAL(version1.isValid(), true);
    BOOST_CHECK_EQUAL(version1.isStable(), false);
    BOOST_CHECK_EQUAL(version1.getVersion(), "1.0.0-alpha");
    BOOST_CHECK_EQUAL(version1.getMajor(), 1);
    BOOST_CHECK_EQUAL(version1.getMinor(), 0);
    BOOST_CHECK_EQUAL(version1.getPatch(), 0);
    BOOST_CHECK_EQUAL(version1.getPreReleaseType(), semver::PRE_RELEASE_ALPHA);
    BOOST_CHECK_EQUAL(version1.getPreRelease(), "alpha");
    BOOST_CHECK_EQUAL(version1.getBuild(), "");
    
    semver::version version2("1.0.0-alpha.1");

    BOOST_CHECK_EQUAL(version2.isValid(), true);
    BOOST_CHECK_EQUAL(version2.isStable(), false);
    BOOST_CHECK_EQUAL(version2.getVersion(), "1.0.0-alpha.1");
    BOOST_CHECK_EQUAL(version2.getMajor(), 1);
    BOOST_CHECK_EQUAL(version2.getMinor(), 0);
    BOOST_CHECK_EQUAL(version2.getPatch(), 0);
    BOOST_CHECK_EQUAL(version2.getPreReleaseType(), semver::PRE_RELEASE_ALPHA);
    BOOST_CHECK_EQUAL(version2.getPreRelease(), "alpha.1");
    BOOST_CHECK_EQUAL(version2.getBuild(), "");

    semver::version version3("1.0.0-rc.1");

    BOOST_CHECK_EQUAL(version3.isValid(), true);
    BOOST_CHECK_EQUAL(version3.isStable(), false);
    BOOST_CHECK_EQUAL(version3.getVersion(), "1.0.0-rc.1");
    BOOST_CHECK_EQUAL(version3.getMajor(), 1);
    BOOST_CHECK_EQUAL(version3.getMinor(), 0);
    BOOST_CHECK_EQUAL(version3.getPatch(), 0);
    BOOST_CHECK_EQUAL(version3.getPreReleaseType(), semver::PRE_RELEASE_RC);
    BOOST_CHECK_EQUAL(version3.getPreRelease(), "rc.1");
    BOOST_CHECK_EQUAL(version3.getBuild(), "");

    semver::version version4("1.0.0-rc-beta.1");

    BOOST_CHECK_EQUAL(version4.isValid(), true);
    BOOST_CHECK_EQUAL(version4.isStable(), false);
    BOOST_CHECK_EQUAL(version4.getVersion(), "1.0.0-rc-beta.1");
    BOOST_CHECK_EQUAL(version4.getMajor(), 1);
    BOOST_CHECK_EQUAL(version4.getMinor(), 0);
    BOOST_CHECK_EQUAL(version4.getPatch(), 0);
    BOOST_CHECK_EQUAL(version4.getPreRelease(), "rc-beta.1");
    BOOST_CHECK_EQUAL(version4.getBuild(), "");
}

BOOST_AUTO_TEST_CASE(test_build_version)
{
    semver::version version("1.2.3-beta+20130101133700");

    BOOST_CHECK_EQUAL(version.isValid(), true);
    BOOST_CHECK_EQUAL(version.isStable(), false);
    BOOST_CHECK_EQUAL(version.getVersion(), "1.2.3-beta+20130101133700");
    BOOST_CHECK_EQUAL(version.getMajor(), 1);
    BOOST_CHECK_EQUAL(version.getMinor(), 2);
    BOOST_CHECK_EQUAL(version.getPatch(), 3);
    BOOST_CHECK_EQUAL(version.getPreRelease(), "beta");
    BOOST_CHECK_EQUAL(version.getBuild(), "20130101133700");

    semver::version version1("1.2.3-rc-beta+20130101133700");

    BOOST_CHECK_EQUAL(version1.isValid(), true);
    BOOST_CHECK_EQUAL(version1.isStable(), false);
    BOOST_CHECK_EQUAL(version1.getVersion(), "1.2.3-rc-beta+20130101133700");
    BOOST_CHECK_EQUAL(version1.getMajor(), 1);
    BOOST_CHECK_EQUAL(version1.getMinor(), 2);
    BOOST_CHECK_EQUAL(version1.getPatch(), 3);
    BOOST_CHECK_EQUAL(version1.getPreRelease(), "rc-beta");
    BOOST_CHECK_EQUAL(version1.getBuild(), "20130101133700");

    semver::version version2("1.2.3+20130101133700");

    BOOST_CHECK_EQUAL(version2.isValid(), true);
    BOOST_CHECK_EQUAL(version2.isStable(), true);
    BOOST_CHECK_EQUAL(version2.getVersion(), "1.2.3+20130101133700");
    BOOST_CHECK_EQUAL(version2.getMajor(), 1);
    BOOST_CHECK_EQUAL(version2.getMinor(), 2);
    BOOST_CHECK_EQUAL(version2.getPatch(), 3);
    BOOST_CHECK_EQUAL(version2.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version2.getBuild(), "20130101133700");

    semver::version version3("1.2.3+20130101133700-foo");

    BOOST_CHECK_EQUAL(version3.isValid(), true);
    BOOST_CHECK_EQUAL(version3.isStable(), true);
    BOOST_CHECK_EQUAL(version3.getVersion(), "1.2.3+20130101133700-foo");
    BOOST_CHECK_EQUAL(version3.getMajor(), 1);
    BOOST_CHECK_EQUAL(version3.getMinor(), 2);
    BOOST_CHECK_EQUAL(version3.getPatch(), 3);
    BOOST_CHECK_EQUAL(version3.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version3.getBuild(), "20130101133700-foo");
}

BOOST_AUTO_TEST_CASE(test_compare)
{
    semver::version version("1.2.3");

    semver::version version1("1.2.3");

    BOOST_CHECK_EQUAL(version.compare(version1), 0);

    semver::version version2("1.2.3");

    semver::version version3("1.2.4");

    BOOST_CHECK_EQUAL(version2.compare(version3), -1);

    BOOST_CHECK_EQUAL(version3.compare(version2), 1);
}

BOOST_AUTO_TEST_CASE(test_assignment)
{
    semver::version version("1.2.3");
    semver::version version2("1.2.4");

    version = version2;

    BOOST_CHECK_EQUAL(version.isValid(), true);
    BOOST_CHECK_EQUAL(version.getVersion(), "1.2.4");
    BOOST_CHECK_EQUAL(version.getMajor(), 1);
    BOOST_CHECK_EQUAL(version.getMinor(), 2);
    BOOST_CHECK_EQUAL(version.getPatch(), 4);
    BOOST_CHECK_EQUAL(version.getPreReleaseType(), semver::PRE_RELEASE_NONE);
    BOOST_CHECK_EQUAL(version.getPreRelease(), "");
    BOOST_CHECK_EQUAL(version.getBuild(), "");
}


BOOST_AUTO_TEST_CASE(test_comparator)
{
    semver::version version("1.2.3-beta+20130101133700");

    semver::version version1("1.2.3-beta+20130101133700");
    
    semver::version version2("1.2.3-beta+20130101133701");

    BOOST_CHECK_EQUAL(version == version1, true);

    BOOST_CHECK_EQUAL(version != version1, false);

    BOOST_CHECK_EQUAL(version == version2, false);

    BOOST_CHECK_EQUAL(version != version2, true);

    semver::version version3("1.2.3");

    semver::version version4("1.2.4");

    BOOST_CHECK_EQUAL(version4 > version3, true);

    semver::version version5("1.2.3");

    semver::version version6("1.3.3");

    BOOST_CHECK_EQUAL(version6 > version5, true);

    semver::version version7("1.2.3");

    semver::version version8("2.2.3");

    BOOST_CHECK_EQUAL(version8 > version7, true);

    semver::version version9("1.2.3-alpha");

    semver::version version10("1.2.3-beta");

    BOOST_CHECK_EQUAL(version10 > version9, true);

    semver::version version11("1.2.3-beta");

    semver::version version12("1.2.3-rc");

    BOOST_CHECK_EQUAL(version12 > version11, true);

    semver::version version13("1.2.3-rc");

    semver::version version14("1.2.3");

    BOOST_CHECK_EQUAL(version14 > version13, true);
    BOOST_CHECK_EQUAL(version14 < version13, false);
    BOOST_CHECK_EQUAL(version13 < version14, true);

    semver::version version15("1.2.3");

    semver::version version16("1.2.3");

    BOOST_CHECK_EQUAL(version15 >= version16, true);
    BOOST_CHECK_EQUAL(version15 <= version16, true);

    semver::version version17("1.2.3");

    semver::version version18("1.2.4");

    BOOST_CHECK_EQUAL(version18 >= version17, true);
    BOOST_CHECK_EQUAL(version17 >= version18, false);
    BOOST_CHECK_EQUAL(version17 <= version18, true);

    semver::version version19("1.2.3-beta");

    semver::version version20("1.2.4-beta.1");

    BOOST_CHECK_EQUAL(version20 > version19, true);
}

BOOST_AUTO_TEST_CASE(test_comparator_suite)
{
    // 1.0.0-alpha < 1.0.0-alpha.1 < 1.0.0-alpha.beta < 1.0.0-beta < 1.0.0-beta.2 < 1.0.0-beta.11 < 1.0.0-rc.1 < 1.0.0.
    semver::version v1alpha("1.0.0-alpha");
    semver::version v1alpha1("1.0.0-alpha.1");
    semver::version v1alphabeta("1.0.0-alpha.beta");
    semver::version v1beta("1.0.0-beta");
    semver::version v1beta2("1.0.0-beta.2");
    semver::version v1beta11("1.0.0-beta.11");
    semver::version v1rc1("1.0.0-rc.1");
    semver::version v1("1.0.0");

    BOOST_CHECK_EQUAL(v1alpha < v1alpha1, true);
    BOOST_CHECK_EQUAL(v1alpha1 < v1alphabeta, true);
    BOOST_CHECK_EQUAL(v1alphabeta < v1beta, true);
    BOOST_CHECK_EQUAL(v1beta < v1beta2, true);
    BOOST_CHECK_EQUAL(v1beta2 < v1beta11, true);
    BOOST_CHECK_EQUAL(v1beta11 < v1rc1, true);
    BOOST_CHECK_EQUAL(v1rc1 < v1, true);
}

BOOST_AUTO_TEST_CASE(test_stream)
{
    std::string semver = "1.2.3-alpha.1";
    semver::version version(semver);

    boost::test_tools::output_test_stream output;

    output << version;

    BOOST_CHECK(output.is_equal(semver));
}

BOOST_AUTO_TEST_SUITE_END()