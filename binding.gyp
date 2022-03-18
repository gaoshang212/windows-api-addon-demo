{
	'targets': [{
		'target_name': 'libWinApi',
		'defines': ['V8_DEPRECATION_WARNINGS=1'],
		'sources': ['libWinApi.cc'		],
		'include_dirs': ["<!(node -e \"require('nan')\")"],
		'conditions': [    
			['OS=="mac"',{
				'make_global_settings': [['CC','/usr/bin/clang'],['CXX','/usr/bin/clang++'],],
				'defines': ['OS_POSIX','OS_MACOSX',],
				'xcode_settings': {
					'ALWAYS_SEARCH_USER_PATHS': 'NO',
					#'i386',
					'x86_64''ARCHS': ['x86_64'],
					'MACOSX_DEPLOYMENT_TARGET': '10.9',
					'CC': 'clang',
					'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
					'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
					#libstdc++, c++11, libc++
					#'CLANG_CXX_LIBRARY': 'libstdc++',
					'GCC_ENABLE_OBJC_GC': 'unsupported',
					#'LIBRARY_SEARCH_PATHS': [],
					'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
					'GCC_SYMBOLS_PRIVATE_EXTERN': 'NO',
					'DEBUG_INFORMATION_FORMAT': 'dwarf-with-dsym',
					#'DEPLOYMENT_POSTPROCESSING': 'YES',
					'OTHER_CFLAGS': ['-fno-eliminate-unused-debug-symbols',
					'-mmacosx-version-min=10.9',
					#compileuseoc++'-xobjective-c++',
					],
					'WARNING_CFLAGS': ['-Wno-deprecated-declarations'],
					'WARNING_CFLAGS!': ['-Wall','-Wextra',],
					'WARNING_CXXFLAGS': ['-Wstrict-aliasing','-Wno-deprecated']
				},
				#xcode_settings'
        'link_settings': {
					'libraries': ['$(SDKROOT)/System/Library/Frameworks/Foundation.framework']
				},
				#configurations
      }]],
		#Mac
	}]
}