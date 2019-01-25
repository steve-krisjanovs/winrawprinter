{
    "targets": [{
        "target_name": "winrawprinter",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "cppsrc/main.cpp",
            "cppsrc/rawprinter.cpp"
        ],
        'msvs_settings': {
            'VCCLCompilerTool': { 'ExceptionHandling': 1 },
        },
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "<!@(node -p \"require('napi-thread-safe-callback').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS-xx' ],
        'conditions': [
            ['OS=="win"', { 'defines': [ '_HAS_EXCEPTIONS=1' ] }]
        ]
    }]
}