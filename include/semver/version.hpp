#pragma once
/**
 * Semver - The Semantic Versioning
 *
 * (c) Axel Etcheverry <axel@etcheverry.biz>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <string>
#include <sstream>

namespace semver {

    enum PRE_RELEASE {
        PRE_RELEASE_ALPHA,
        PRE_RELEASE_BETA,
        PRE_RELEASE_RC,
        PRE_RELEASE_NONE
    };

    typedef enum PRE_RELEASE pre_release_t;

    class version
    {
    private:
        std::string m_version;
        int m_major;
        int m_minor;
        int m_patch;
        pre_release_t m_pre_release_type;
        std::string m_pre_release;
        std::string m_build;
        bool m_is_valid;

        enum m_type {
            TYPE_MAJOR,
            TYPE_MINOR,
            TYPE_PATCH,
            TYPE_PRE_RELEASE,
            TYPE_BUILD
        };

        void parse()
        {
            int type = TYPE_MAJOR;

            std::string major, minor, patch;

            for (std::size_t i = 0; i < m_version.length(); i++)
            {
                char chr = m_version[i];
                int chr_dec = chr;

                switch (type)
                {
                    case TYPE_MAJOR:

                        if (chr == '.')
                        {
                            type = TYPE_MINOR;
                            continue;
                        }

                        if (chr_dec < 48 || chr_dec > 57)
                        {
                            m_is_valid = false;
                        }

                        // major
                        major += chr;
                        break;

                    case TYPE_MINOR:

                        if (chr == '.')
                        {
                            type = TYPE_PATCH;
                            continue;
                        }

                        if (chr_dec < 48 || chr_dec > 57)
                        {
                            m_is_valid = false;
                        }

                        minor += chr;

                        break;

                    case TYPE_PATCH:

                        if (chr == '-')
                        {
                            type = TYPE_PRE_RELEASE;
                            continue;
                        }

                        if (chr == '+')
                        {
                            type = TYPE_BUILD;
                            continue;
                        }


                        if (chr_dec < 48 || chr_dec > 57)
                        {
                            m_is_valid = false;
                        }

                        patch += chr;

                        break;

                    case TYPE_PRE_RELEASE:
                        
                        if (chr == '+' || chr == '.')
                        {
                            type = TYPE_BUILD;
                            continue;
                        }

                        if (
                            (chr_dec < 48 || chr_dec > 57) && // 0-9
                            (chr_dec < 65 || chr_dec > 90) && // A-Z
                            (chr_dec < 97 || chr_dec > 122) && // a-z
                            (chr_dec != 45) // -
                        )
                        {
                            m_is_valid = false;
                        }

                        m_pre_release += chr;
                        break;

                    case TYPE_BUILD:

                        if (
                            (chr_dec < 48 || chr_dec > 57) && // 0-9
                            (chr_dec < 65 || chr_dec > 90) && // A-Z
                            (chr_dec < 97 || chr_dec > 122) && // a-z
                            (chr_dec != 45) // -
                        )
                        {
                            m_is_valid = false;
                        }

                        m_build += chr;
                        break;
                }
            }

            if (m_is_valid)
            {
                std::istringstream(major) >> m_major;
                std::istringstream(minor) >> m_minor;
                std::istringstream(patch) >> m_patch;

                if (m_pre_release.empty())
                {
                    m_pre_release_type = PRE_RELEASE_NONE;
                }
                else if (m_pre_release.compare("alpha") == 0)
                {
                    m_pre_release_type = PRE_RELEASE_ALPHA;
                } 
                else if (m_pre_release.compare("beta") == 0)
                {
                    m_pre_release_type = PRE_RELEASE_BETA;
                }
                else if (m_pre_release.compare("rc") == 0)
                {
                    m_pre_release_type = PRE_RELEASE_RC;
                }
            }

            if (m_major == 0 && m_minor == 0 && m_patch == 0)
            {
                m_is_valid = false;
            }
        }

    public:
        version(const std::string& version)
        {
            m_version = version;
            m_major = 0;
            m_minor = 0;
            m_patch = 0;
            m_build = "";
            m_pre_release = "";

            if (version.empty())
            {
                m_is_valid = false;
            }
            else
            {
                m_is_valid = true;

                parse();
            }
        }

        ~version() {}
    
        std::string getVersion()
        {
            return m_version;
        }

        int getMajor()
        {
            return m_major;
        }

        int getMinor()
        {
            return m_minor;
        }

        int getPatch()
        {
            return m_patch;
        }

        std::string getBuild()
        {
            return m_build;
        }

        pre_release_t getPreReleaseType()
        {
            return m_pre_release_type;
        }

        std::string getPreRelease()
        {
            return m_pre_release;
        }

        bool isValid()
        {
            return m_is_valid;
        }

        int compare(version& rgt)
        {

            if ((*this) == rgt)
            {
                return 0;
            }

            if ((*this) > rgt)
            {
                return 1;
            }

            return -1;
        }

        friend bool operator== (version &lft, version &rgt);
        friend bool operator!= (version &lft, version &rgt);
        friend bool operator> (version &lft, version &rgt);
        friend bool operator>= (version &lft, version &rgt);
        friend bool operator< (version &lft, version &rgt);
        friend bool operator<= (version &lft, version &rgt);
    };

    bool operator== (version& lft, version& rgt)
    {
        return lft.getVersion().compare(rgt.getVersion()) == 0;
    }

    bool operator!= (version& lft, version& rgt)
    {
        return !(lft == rgt);
    }

    bool operator> (version& lft, version& rgt)
    {
        // Major
        if (lft.getMajor() < 0 && rgt.getMajor() >= 0)
        {
            return false;
        }

        if (lft.getMajor() >= 0 && rgt.getMajor() < 0)
        {
            return true;
        }

        if (lft.getMajor() > rgt.getMajor())
        {
            return true;
        }

        if (lft.getMajor() < rgt.getMajor())
        {
            return false;
        }


        // Minor
        if (lft.getMinor() < 0 && rgt.getMinor() >= 0)
        {
            return false;
        }

        if (lft.getMinor() >= 0 && rgt.getMinor() < 0)
        {
            return true;
        }

        if (lft.getMinor() > rgt.getMinor())
        {
            return true;
        }

        if (lft.getMinor() < rgt.getMinor())
        {
            return false;
        }


        // Patch
        if (lft.getPatch() < 0 && rgt.getPatch() >= 0)
        {
            return false;
        }

        if (lft.getPatch() >= 0 && rgt.getPatch() < 0)
        {
            return true;
        }

        if (lft.getPatch() > rgt.getPatch())
        {
            return true;
        }

        if (lft.getPatch() < rgt.getPatch())
        {
            return false;
        }

        /**
         * 1.0.0-alpha < 1.0.0-alpha.1 < 1.0.0-alpha.beta < 1.0.0-beta < 1.0.0-beta.2 < 1.0.0-beta.11 < 1.0.0-rc.1 < 1.0.0.
         */
        
        // Pre release
        if (lft.getPreReleaseType() == rgt.getPreReleaseType())
        {
            return false;
        }

        if (lft.getPreReleaseType() > rgt.getPreReleaseType())
        {
            return true;
        }

        
        /*if (lft.getPreRelease().compare(rgt.getPreRelease()) == 0)
        {
            return false;
        }

        if (lft.getPreRelease().empty() && !rgt.getPreRelease().empty())
        {
            return true;
        }

        if (!lft.getPreRelease().empty() && rgt.getPreRelease().empty())
        {
            return false;
        }*/

        //@TODO implement and build

        return false;
    }

    bool operator>= (version& lft, version& rgt)
    {
        return (lft > rgt) || (lft == rgt);
    }

    bool operator< (version& lft, version& rgt)
    {
        return (rgt > lft);
    }

    bool operator<= (version& lft, version& rgt)
    {
        return (lft < rgt) || (lft == rgt);
    }

} // end semver namespace
