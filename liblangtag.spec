%global girname LangTag
%global girapiversion 0.6

Name: liblangtag
Version: 0.6.2
Release: 1.1%{?dist}
Summary: An interface library to access tags for identifying languages

License: (LGPLv3+ or MPLv2.0) and UCD
URL: http://tagoh.bitbucket.org/liblangtag/
Source0: https://bitbucket.org/tagoh/%{name}/downloads/%{name}-%{version}.tar.bz2

BuildRequires: glibc-common
BuildRequires: gtk-doc
BuildRequires: libtool
BuildRequires: pkgconfig(check)
BuildRequires: pkgconfig(gobject-2.0)
BuildRequires: pkgconfig(gobject-introspection-1.0)
BuildRequires: pkgconfig(libxml-2.0)

%description
%{name} is an interface library to access tags for identifying
languages.

Features:
* several subtag registry database supports:
  - language
  - extlang
  - script
  - region
  - variant
  - extension
  - grandfathered
  - redundant
* handling of the language tags
  - parser
  - matching
  - canonicalizing

%package gobject
Summary: GObject introspection for %{name}
Requires: %{name}%{?_isa} = %{version}-%{release}

%description gobject
The %{name}-gobject package contains files for GObject introspection for
%{name}.

%package devel
Summary: Development files for %{name}
Requires: %{name}%{?_isa} = %{version}-%{release}
Requires: %{name}-gobject%{?_isa} = %{version}-%{release}

%description devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.

%package doc
Summary: Documentation of %{name} API
BuildArch: noarch

%description doc
The %{name}-doc package contains documentation files for %{name}.

%prep
%setup -q

%build
%configure --disable-silent-rules --disable-static --enable-shared --enable-introspection
sed -i \
    -e 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' \
    -e 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' \
    libtool
export LD_LIBRARY_PATH=`pwd`/liblangtag/.libs:`pwd`/liblangtag-gobject/.libs${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
make %{?_smp_mflags}
# workaround gnome-introspection bug that causes multilib problems
sed -i \
    -e 's/lt_pointer_t/LtPointer/' \
    -e 's/lt_grandfathered_t/LtGrandfathered/' \
    -e 's/lt_redundant_t/LtRedundant/' \
    -e 's/lt_variant_t/LtVariant/' \
    -e 's/lt_extlang_t/LtExtlang/' \
    -e 's/lt_script_t/LtScript/' \
    -e 's/lt_lang_t/LtLang/' \
    liblangtag-gobject/%{girname}-%{girapiversion}.gir

%install
make install DESTDIR=%{buildroot}
rm -f %{buildroot}/%{_libdir}/*.la %{buildroot}/%{_libdir}/%{name}/*.la

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%check
export LD_LIBRARY_PATH=`pwd`/liblangtag/.libs:`pwd`/liblangtag-gobject/.libs${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
make %{?_smp_mflags} check

%files
%doc AUTHORS COPYING NEWS README
%{_libdir}/%{name}.so.*
%{_libdir}/%{name}/*.so
%{_datadir}/%{name}

%files gobject
%{_libdir}/%{name}-gobject.so.*
%{_libdir}/girepository-1.0/%{girname}-%{girapiversion}.typelib

%files devel
%{_includedir}/%{name}
%{_libdir}/%{name}.so
%{_libdir}/%{name}-gobject.so
%{_libdir}/pkgconfig/%{name}.pc
%{_libdir}/pkgconfig/%{name}-gobject.pc
%{_datadir}/gir-1.0/%{girname}-%{girapiversion}.gir

%files doc
%doc COPYING
%{_datadir}/gtk-doc/html/%{name}

%changelog
* Mon Sep 11 2017 Akira TAGOH <tagoh@redhat.com> - 0.6.2-1.1
- Resolves: rhbz#1477212 Fix multilib issue.

* Mon Sep 11 2017 Akira TAGOH <tagoh@redhat.com> - 0.6.2-1
- Resolves: rhbz#1477212 Rebase to 0.6.2.

* Fri Nov 07 2014 David Tardon <dtardon@redhat.com> - 0.5.4-8
- Related: rhbz#1132077 really resolve multilib conflict in -devel

* Fri Nov 07 2014 David Tardon <dtardon@redhat.com> - 0.5.4-7
- Related: rhbz#1132077 resolve multilib conflict in -devel

* Fri Sep 05 2014 David Tardon <dtardon@redhat.com> - 0.5.4-6
- Related: rhbz#1132077 add explicit dep on -gobject to -devel

* Fri Sep 05 2014 David Tardon <dtardon@redhat.com> - 0.5.4-5
- split GObject introspection files out of main package

* Fri Sep 05 2014 David Tardon <dtardon@redhat.com> - 0.5.3-1
- Resolves: rhbz#1132077 rebase to 0.5.4

* Fri Jan 24 2014 Daniel Mach <dmach@redhat.com> - 0.5.1-4
- Mass rebuild 2014-01-24

* Fri Dec 27 2013 Daniel Mach <dmach@redhat.com> - 0.5.1-3
- Mass rebuild 2013-12-27

* Thu May 16 2013 Eike Rathke <erack@redhat.com> - 0.5.1-2-UNBUILT
- updated .spec with MPLv2.0 and UCD licenses

* Tue Apr 30 2013 David Tardon <dtardon@redhat.com> - 0.5.1-1
- fix ABI breakage

* Mon Apr 29 2013 David Tardon <dtardon@redhat.com> - 0.5.0-1
- new release

* Thu Feb 14 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.4.0-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_19_Mass_Rebuild

* Sat Dec 01 2012 David Tardon <dtardon@redhat.com> - 0.4.0-2
- fix build on ppc

* Sun Nov 25 2012 David Tardon <dtardon@redhat.com> - 0.4.0-1
- new upstream release

* Sun Sep 09 2012 David Tardon <dtardon@redhat.com> - 0.3-1
- initial import
