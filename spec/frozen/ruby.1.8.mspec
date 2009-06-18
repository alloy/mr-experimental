# Configuration file for Ruby 1.8-compatible Ruby implementations.
#
# Unless you passed to --config (or -B) to MSpec, MSpec will automatically
# use this config file if the Ruby interpreter with which MSpec advertises
# itself with RUBY_VERSION =~ /1.8/

class MSpecScript
  # Language features specs
  set :language, [ 'language' ]

  # Core library specs
  set :core, [
    'core',

    # 1.9
    '^core/basicobject'
  ]

  # Standard library specs
  set :library, [
    'library',

    # 1.9 feature
    '^library/cmath',
    '^library/continuation',
    '^library/coverage',
    '^library/fiber',
    '^library/json',
    '^library/minitest',
    '^library/prime',
    '^library/ripper',
    '^library/rake',
    '^library/rubygems',
  ]

  # An ordered list of the directories containing specs to run
  set :files, get(:language) + get(:core) + get(:library)

  # Optional library specs
  set :ffi, 'optional/ffi'

  # A list of _all_ optional library specs
  set :optional, [get(:ffi)]

  # The default implementation to run the specs
  set :target, 'ruby'

  set :tags_patterns, [
                        [%r(language/),     'tags/1.8/language/'],
                        [%r(core/),         'tags/1.8/core/'],
                        [%r(command_line/), 'tags/1.8/command_line/'],
                        [%r(library/),      'tags/1.8/library/'],
                        [/_spec.rb$/,       '_tags.txt']
                      ]
end
