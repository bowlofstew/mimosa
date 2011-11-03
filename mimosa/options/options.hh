#ifndef MIMOSA_OPTIONS_OPTIONS_HH
# define MIMOSA_OPTIONS_OPTIONS_HH

# include <string>
# include <sstream>

namespace mimosa
{
  namespace options
  {
    class BasicOption
    {
    public:
      BasicOption(const char * group,
                  const char * name,
                  const char * desc)
        : group_(group), name_(name), desc_(desc)
      {
      }

      virtual bool parse(int & argc, char **& argv) = 0;

      std::string group_;
      std::string name_;
      std::string desc_;
    };

    class SwitchOption : public BasicOption
    {
    public:
      SwitchOption(const char * group,
                   const char * name,
                   const char * desc)
        : BasicOption(name, group, desc), value_(false)
      {
      }

      virtual bool parse(int &, char **&)
      {
        value_ = true;
        return true;
      }

      bool value_;
    };

    template <typename T>
    class Option : public BasicOption
    {
    public:
      Option(const char * group,
             const char * name,
             const char * desc,
             T            default_value)
        : BasicOption(name, group, desc), value_(default_value)
      {
      }

      virtual bool parse(int & argc, char **& argv)
      {
        if (argc < 1)
          return false;

        std::istringstream is(*argv);
        is >> value_;

        --argc;
        ++argv;

        return !is.fail();
      }

      T           value_;
    };

    void parse(int argc, char ** argv);
    void addOption(BasicOption * option);

    template <typename T>
    inline
    T * addOption(const char * group,
                  const char * name,
                  const char * desc,
                  T            default_value)
    {
      auto opt = new Option<T>(group, name, desc, default_value);
      addOption(opt);
      return &opt->value_;
    }

    inline
    bool * addSwitch(const char * group,
                     const char * name,
                     const char * desc)
    {
      auto opt = new SwitchOption(group, name, desc);
      addOption(opt);
      return &opt->value_;
    }
  }
}

#endif /* !MIMOSA_OPTIONS_OPTIONS_HH */
